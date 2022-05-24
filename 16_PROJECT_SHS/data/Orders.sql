SELECT
qheader."ACCOUNT_ID",
header."Active (Flag)",
header."ISO",
header."Order Date",
header."Order Status",
header."Sales Document Number RC",
header."Type",
CAST(det."ACCOUNT_ID (Bill-To)" AS CHAR(15)) AS "ACCOUNT_ID (Bill-To)",
CAST(det."ACCOUNT_ID (End-User)" AS CHAR(15)) AS "ACCOUNT_ID (End-User)",
CAST(det."ACCOUNT_ID (Pay-To)" AS CHAR(15)) AS "ACCOUNT_ID (Pay-To)",
CAST(det."ACCOUNT_ID (Ship-To)" AS CHAR(15)) AS "ACCOUNT_ID (Ship-To)",
CAST(det."ACCOUNT_ID (Sold-To)" AS CHAR(15)) AS "ACCOUNT_ID (Sold-To)",
det."ERP Order Number",
det."Order Number",
det."Order Sale Type",
det."Quote Number and Revision",
SUM(det."Order Total Net Value") AS "Order Total Net Value",
SUM(det."Order Quantity") AS "Order Quantity"
FROM CRMCL_TOPICAREA.CPQ."Order_Details" det 
LEFT JOIN CRMCL_TOPICAREA.CPQ.ACTIVE_QUOTES_HEADER qheader ON det."Quote Number and Revision" = qheader."Quote Number and Revision" 
LEFT JOIN CRMCL_TOPICAREA.CPQ."Orders" header ON det."Quote Number and Revision" = header."Quote Number and Revision" 
WHERE qheader."ACCOUNT_ID" IN (
{0}
)
GROUP BY
qheader."ACCOUNT_ID",
header."Active (Flag)",
header."ISO",
header."Order Date",
header."Order Status",
header."Sales Document Number RC",
header."Type",
"ACCOUNT_ID (Bill-To)",
"ACCOUNT_ID (End-User)",
"ACCOUNT_ID (Pay-To)",
"ACCOUNT_ID (Ship-To)",
"ACCOUNT_ID (Sold-To)",
det."ERP Order Number",
det."Order Number",
det."Order Sale Type",
det."Quote Number and Revision"