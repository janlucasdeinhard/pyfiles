SELECT
header."ACCOUNT_ID",
header."CPQ.Last Updated Timestamp",
header."CPR (Flag)",
header."DSO (Quote)",
header."DXCON.Approval Level",
header."DXCON.CPR Deal (Flag)",
header."DXCON.Configuration Approved (Flag)",
header."DXCON.Deal Billing Option",
header."DXCON.Deal Finance Option",
header."DXCON.Deal Finance Type",
header."DXCON.Deal Locked (Flag)",
header."DXCON.Last Saved Timestamp",
header."DXCON.Manual Discount (Flag)",
header."DXCON.Pricing Approved (Flag)",
header."DXCON.Sales Contract Duration (in months)",
header."Data Issue Comment",
header."Data Quality Issue (Flag)",
header."Has Automation (Flag)",
header."Has Instrument (Flag)",
header."Implausible Cost (Flag)",
header."Implausible Revenue (Flag)",
header."OPPORTUNITY_ID",
header."Opportunity Expired (Flag)",
header."Possible Test Quote (Flag)",
header."Quote Active (Flag)",
header."Quote Number and Revision",
header."Quote Status",
header."Quote Type",
header."Quote.Business Type",
header."Quote.Created Timestamp",
header."Quote.ISO",
header."Tender Type",
0 AS "Total Cost (GC)",
0 AS "Total Revenue (GC)"
FROM CRMCL_TOPICAREA.CPQ.ACTIVE_QUOTES_HEADER header
LEFT JOIN CRMCL_TOPICAREA.CPQ."IN_VIVO_Quote_Details" rev ON header."Quote Number and Revision"=rev."Quote Number and Revision" 
LEFT JOIN CRMCL_TOPICAREA.CPQ."IN_VIVO_QuoteItem_Costs" costs ON header."Quote Number and Revision" = costs."Quote Number and Revision" 
WHERE header."Quote Type" = 'SERVICES'
AND header."ACCOUNT_ID" IN (
{0}
)