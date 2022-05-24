SELECT
"ACCOUNT_ID",
"ASSET_ID",
"LEAD_ID",
"Last Automatic Assignment Date",
"Lead Age in Days",
"Lead Origin",
"Lead.Close Date",
"Lead.Contact Email",
"Lead.Contact First Name",
"Lead.Contact Job Role",
"Lead.Contact Job Title",
"Lead.Contact Last Name",
"Lead.Contact Postal Code",
"Lead.Country",
"Lead.Created Timestamp",
"Lead.FL Number",
"Lead.IB Vendor",
"Lead.Last Updated Timestamp",
"Lead.Opportunity Type",
"Lead.Sale Type",
"Lead.Sales Product Line",
"Lead.Status",
"PRODUCT_ID"
FROM CRMCL_TOPICAREA.OSC."Leads" 
WHERE "ACCOUNT_ID" IN (
{0}
)