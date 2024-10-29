//________________________________________________________________________________Google Apps Script
function doGet(e) { 
  Logger.log(JSON.stringify(e));
  var result = 'Ok';
  if (typeof e.parameter === 'undefined') {
    result = 'No Parameters';
  }
  else {
    var sheet_id = '1DAcC1ekiehjSFaSDNk1JmukOC9fG-Y4tADqwi9kRdF8'; 	// Spreadsheet ID.
    var sheet_name = "Sheet5";  // Sheet Name in Google Sheets.

    var sheet_open = SpreadsheetApp.openById(sheet_id);
    var sheet_target = sheet_open.getSheetByName(sheet_name);

    var newRow = sheet_target.getLastRow() + 1;

    var rowDataLog = [];

    var Data_for_A3;
    var Data_for_B3;
    var Data_for_C3;
    var Data_for_D3;
    var Data_for_E3;
    var Data_for_F3;

    var Curr_Date = Utilities.formatDate(new Date(), "Asia/Kolkata", 'dd/MM/yyyy');
    rowDataLog[0] = Curr_Date;  // Date will be written in column A (in the "DHT11 Sensor Data Logger" section).

    var Curr_Time = Utilities.formatDate(new Date(), "Asia/Kolkata", 'HH:mm:ss');
    rowDataLog[1] = Curr_Time;  // Time will be written in column B (in the "DHT11 Sensor Data Logger" section).

    var sts_val = '';

    for (var param in e.parameter) {
      Logger.log('param: ' + param); // Log the parameter name
      var value = stripQuotes(e.parameter[param]);
      Logger.log(param + ':' + e.parameter[param]);
      switch (param) {
        case 'sts':
          sts_val = value;
          break;

        case 'medinf':
          rowDataLog[2] = value;
          result += ', medinf Written on column C';
          break;

        case 'mfg':
          rowDataLog[3] = value;
          result += ', mfg Written on column D';
          break;

        case 'exp':
          rowDataLog[4] = value;
          result += ', exp Written on column E';
          break;

        case 'sta':
          rowDataLog[5] = value;
          result += ', sta Written on column F';
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

function stripQuotes(value) {
  return value.replace(/^["']|['"]$/g, "");
}
