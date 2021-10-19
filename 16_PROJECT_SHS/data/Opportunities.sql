SELECT
"ACCOUNT_ID",
"Calculated Expected Turnover Date (earliest)",
"Calculated Expected Turnover Date (latest)",
"Calculated Revenue Start Date (earliest)",
"Calculated Revenue Start Date (latest)",
"Calculated Shipment Date (earliest)",
"Calculated Shipment Date (latest)",
"Direct/Partner Business",
"Indirect Business Type",
"OLI.Close Date (earliest)",
"OLI.Close Date (latest)",
"OPPORTUNITY_ID",
"OPPORTUNITY_ID (Alternate Opportunity)",
"OPPORTUNITY_ID (Linked Opportunity)",
"Opportunity Expired (Flag)",
"Oppty Name",
"Oppty Number",
"Oppty Type",
"Oppty.Close Date",
"Oppty.Created Timestamp",
"Oppty.Forecast Status (Consolidated)",
"Oppty.IT/Automation Included (Flag)",
"Oppty.Lease End Date",
"Oppty.Project Progress",
"Oppty.Quote Number",
"Oppty.Status (Consolidated)",
"Part of ES Project (Flag)",
"Sale Type (Oppty Level)",
"Sales Program (Oppty Level)"
FROM CRMCL_TOPICAREA.OSC."Opportunities" 
WHERE "ACCOUNT_ID" IN (
{0}
)