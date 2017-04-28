//sucessfull
var request = require('request');
var access_token_DRS;
var https = require('https');
var deviceStatus_function = function Device_function(access_token_DRS) {

    var today = new Date();
    //var yesterday = new Date(today.getTime() - (1000*60*60*24));
    //var hourago = new Date(today.getTime() - (1000 * 60 * 60));

    var isoDate = new Date();
    var data = JSON.stringify({
        mostRecentlyActiveDate: isoDate
    });

    var options = {
        hostname: 'dash-replenishment-service-na.amazon.com',
        port: 443,
        path: '/deviceStatus',
        method: 'POST',
        headers: {
            'Authorization': 'Bearer ' + access_token_DRS, //"Atza|IwEBIEnyPh02peJw0OCmDOuIhB77-CezF_T7FrerO5pKmf46wV_rFft6tJOl-qv807h-CWyuw7Zg26WXq2nr7_eITR12oXzfevauOYjCDQ8N3aoQ1WUsrDs6iPbv7UWehqkvX0PtYWbcxbpwPdrk9q-fThCidiuQWcRjL8YTOzYwUGgN6_k9-gpKcQaGt8zKdtRk_MHbGR5bEbR1rnQ1hKTTPlGDTfjNhKLHL8EyJkyPQcJgqEPjMh-7J8PlEOu5JAK_p8JvMjuUxyDSeh8Otdm-Br9E2mXOvpY_Q4mM2A4tp3336d0gFSLxWAJQa3b0d160WHdH1v4x6KGEdkRRdXLw8uNND4I0B7Dc0IDJAwySfZy5TGQfMaLm96wHsL1GRKjgzXgw6kIidF0pvmkeTcAnKraN1EcY91oK1kZMaQ9laGGpYg",
            'x-amzn-accept-type': 'com.amazon.dash.replenishment.DrsDeviceStatusResult@1.0',
            'x-amzn-type-version': 'com.amazon.dash.replenishment.DrsDeviceStatusInput@1.0',
            'Content-Type': 'application/json',
            'Content-Length': Buffer.byteLength(data)
        }
    };

    var req = https.request(options, function(res) {
        res.setEncoding('utf8');
        res.on('data', function(chunk) {
              console.log('\n');
            console.log(isoDate);
            console.log(data);
    console.log('\n');
           console.log(today);
          //  console.log(yesterday);
          //  console.log(hourago);
            console.log('statusCode:', res.statusCode);
            console.log("body: " + chunk);
            console.log("Called Device status successfully");
    console.log('\n');

        });
    });

    req.write(data);
    req.end();
}
exports.deviceStatus_function = deviceStatus_function;
