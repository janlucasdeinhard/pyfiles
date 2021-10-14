SELECT
"ACCOUNT_ID",
"ACCOUNT_ID (MainAccount)",
"ACCOUNT_ID (Parent)",
"Account Address",
"Account Country",
"Account Name",
"Account Name (MainAccount)",
"Account Postal Code",
"Blocking Status",
"CKAP (Flag)",
"Is Partner (Flag)",
"Legal Structure",
"OSC Account Number",
"RKAP (Flag)",
"SAP-ID",
"SAP-ID In Vitro"
FROM CRMCL_TOPICAREA.OSC."Accounts" 
WHERE "ACCOUNT_ID" IN (
{0}
)