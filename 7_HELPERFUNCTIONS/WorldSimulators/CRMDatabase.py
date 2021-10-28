import numpy as np
import os
import pandas as pd
import snowflake.connector

class CRMDB():
    
    def __init__(self,sql_path='./data/',main_account_restrict=10):
        # Data init
        self.sql_path = sql_path
        self.main_account_restrict = main_account_restrict
        self.frames = {}
        # Load frames
        self.load_dataframes()
        # Generate metadata once intially
        self.generate_metadata()
        # Update based on metdata
        self.unify_keycols()
        # Finally re-generate meta-data in final draft, overwriting first draft
        self.generate_metadata()
        return
    
    def load_dataframes(self):
        # Make connection
        conn = snowflake.connector.connect(
            user='jan-lucas.deinhard@siemens-healthineers.com',
            account='shsitdl.west-europe.azure',
            authenticator='externalbrowser'
        )
        # Load accounts subset
        sqlQuery = self.load_sql('accID.sql').format(self.main_account_restrict)
        self.acc_subset_ = '\''+'\',\''.join([str(k) for k in pd.read_sql(sqlQuery,con=conn)['ACCOUNT_ID'].tolist()])+'\''
        # List account files
        sql_files = [k for k in os.listdir(self.sql_path) if k.endswith('.sql')]
        sql_files.remove('accID.sql')
        # Iterate all available SQLs
        for cTargetFile in sql_files:
            cQuery = self.load_sql(cTargetFile)
            cName = cTargetFile.split('.')[0]
            self.frames[cName] = pd.read_sql(cQuery.format(self.acc_subset_),con=conn)
        # Concatenate Installed Base
        self.frames['InstalledBase'] = pd.concat([
            self.frames['InstalledBaseAssets'],
            self.frames['InstalledBaseSDTB']
        ],axis=0)
        del self.frames['InstalledBaseAssets']
        del self.frames['InstalledBaseSDTB']
        # Concatenate Quotes
        self.frames['Quotes'] = pd.concat([
            self.frames['QuotesVivo'],
            self.frames['QuotesVitro'],
            self.frames['QuotesService']
        ],axis=0)
        # Remove originally loaded frames
        del self.frames['QuotesVivo']
        del self.frames['QuotesVitro']
        del self.frames['QuotesService']
        # Close connection
        conn.close()
        return
    
    def load_sql(self,name):
        fd = open('{0}{1}'.format(self.sql_path,name),'r')
        sqlQuery = fd.read()
        fd.close()
        return sqlQuery
    
    def generate_metadata(self):
        # Iterate over all tables and within tables over columns
        L = []
        for ckey in self.frames.keys():
            for tablekey in self.frames[ckey].columns:
                L.append((ckey,tablekey,self.frames[ckey][tablekey].dtype))
        # Store into Data Frame
        self.metadata = pd.DataFrame(L).rename(columns={
            0:'TABLE',
            1:'COLUMN',
            2:'DTYPE'
        })
        # Count multiple occurrences of names
        self.metadata = self.metadata.merge(
            self.metadata[['TABLE','COLUMN']].groupby(['COLUMN']).count(),
            left_on='COLUMN',right_index=True,how='left'
        ).rename(columns={
            'TABLE_x':'TABLE',
            'TABLE_y':'COLUMNCOUNT'
        })
        # Flag likely keys
        self.metadata['ISKEY'] = self.metadata['COLUMN'].apply(lambda x: 'Y' if (('_ID' in x) or (x=='Quote Number and Revision')) else 'N')
        # Done
        return
    
    def unify_keycols(self):
        # Iterate over all rows and adjust data type to object for key columns
        for rownum,k in self.metadata[(self.metadata['ISKEY']=='Y')&(self.metadata['DTYPE']!='object')].iterrows():
            self.frames[k.TABLE][k.COLUMN] = self.frames[k.TABLE][k.COLUMN].apply(lambda x: str(x).split('.')[0] if not np.isnan(x) else np.nan)
        return