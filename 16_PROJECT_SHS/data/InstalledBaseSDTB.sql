SELECT 
"ACCOUNT_ID",
"Asset FL Number",
YEAR("Asset Installation Date") AS "Asset Install Year",
"Asset Material Number",
"Asset Service Contract End Date",
"Asset Service Contract Start Date",
"Asset System EoS Date",
"Asset Waranty End Date",
"Last Updated Date" AS "Asset.Last Updated Timestamp",
"Equipment Status" AS "Asset.Status",
"Equipment Number",
"IB Product" AS "PRODUCT_ID"
FROM CRMCL_TOPICAREA.SDTB.SDTB_IBD 
WHERE "Deleted Asset (Flag)" <> 'Y' 
AND "Demo (Flag)" <> 'Y'
AND "ACCOUNT_ID" IN (
{0}
)