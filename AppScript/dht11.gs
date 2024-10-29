//________________________________________________________________________________Google Apps Script
function doGet(e) { 
  Logger.log(JSON.stringify(e)); // Log incoming request for debugging.
  var result = 'Ok';

  // Check if any parameters are provided.
  if (typeof e.parameter === 'undefined') {
    result = 'No Parameters'; // No parameters in the request.
  }
  else {
    var sheet_id = '1DAcC1ekiehjSFaSDNk1JmukOC9fG-Y4tADqwi9kRdF8'; 	// Spreadsheet ID.
    var sheet_name = "Sheet6";  // Sheet Name in Google Sheets.

    var sheet_open = SpreadsheetApp.openById(sheet_id); // to open sheet with sheet_id
    var sheet_target = sheet_open.getSheetByName(sheet_name); // to open 

    var newRow = sheet_target.getLastRow() + 1;

    var rowDataLog = [];

    var Data_for_A3;
    var Data_for_B3;
    var Data_for_C3;
    var Data_for_D3;

    var Curr_Date = Utilities.formatDate(new Date(), "Asia/Kolkata", 'dd/MM/yyyy');
    rowDataLog[0] = Curr_Date;  // Date will be written in column A (in the "DHT11 Sensor Data Logger" section).

    var Curr_Time = Utilities.formatDate(new Date(), "Asia/Kolkata", 'HH:mm:ss');
    rowDataLog[1] = Curr_Time;  // Time will be written in column B (in the "DHT11 Sensor Data Logger" section).

    var sts_val = '';

    for (var param in e.parameter) {
      Logger.log('In for loop, param=' + param);
      var value = stripQuotes(e.parameter[param]);
      Logger.log(param + ':' + e.parameter[param]);
      switch (param) {
        case 'sts':
          sts_val = value;
          break;

        case 'temp':
          rowDataLog[2] = value;  // Sensor Reading Status will be written in column C (in the "DHT11 Sensor Data Logger" section).
          result += ', temp Written on column C';
          break;

        case 'humi':
          rowDataLog[3] = value;  // The temperature value will be written in column D (in the "DHT11 Sensor Data Logger" section).
          result += ', humidity Written on column D';
          break;

        default:
          result += ", unsupported parameter";
      }
    }
    
    // Conditions for writing data received from ESP32 to Google Sheets.
    if (sts_val == 'write') {
      // Writes data to the "DHT11 Sensor Data Logger" section.
      Logger.log(JSON.stringify(rowDataLog));
      var newRangeDataLog = sheet_target.getRange(newRow, 1, 1, rowDataLog.length);
      newRangeDataLog.setValues([rowDataLog]);
      return ContentService.createTextOutput(result);
    }
      
  }
    
}
function stripQuotes( value ) {
  return value.replace(/^["']|['"]$/g, "");
} 
