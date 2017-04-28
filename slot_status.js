

//sucessfull

var request = require('request');
var access_token_DRS;
var Last_purchase_time_slot;
var remainingQuantity_slot;
var originalQuantity_slot;

var Slot_Status_function = function access_token_function(access_token_DRS ,Last_purchase_time_slot,remainingQuantity_slot,originalQuantity_slot ) {
var https = require('https');
var today = new Date();
var Expected = new Date(today.getTime() + (1000*60*60*24));
var few_time_ago = Last_purchase_time_slot //new Date(today.getTime() - (1000*60*60));
var remainingQuantity_slot_int=parseInt(remainingQuantity_slot);
var originalQuantity_slot_int=parseInt(originalQuantity_slot);

var data = JSON.stringify({
  expectedReplenishmentDate : Expected,
  remainingQuantityInUnit : remainingQuantity_slot_int,
  originalQuantityInUnit : 10,
  totalQuantityOnHand : 20,
  lastUseDate : few_time_ago
  });

var options = {
  hostname: 'dash-replenishment-service-na.amazon.com',
  port: 443,
  path: '/slotStatus/bf3f0b71-7851-4b8c-9c6c-7364118d130f' ,
  method: 'POST',

  headers: {'Authorization' : 'Bearer ' + access_token_DRS, //"Atza|IwEBID4GwCjF-nX6Zhj6du-RHgHetMqSiwYFU7A3N7LzBrd5NRNyzOB5FfjInLEJUSFGi1Zg0VOImCd1DxmxdOTCXoxfQ9xllJv3zl5ue9i6zQMw6wWoz8L36OmOoJlv32bVcLXs5he1aR2s0PKB9w_VUetNj_Y8TLqK3zKC0ZCMdMU3ektVKiF8A8qUqMiq4zaLnXeE2oJdeFNHtzmfY7K-nMb5xJKX7Xx2w8pY-9DE4qylxsRhK6j2hlIXlpp8WyCw4Tiws841idLavlgg1sQb-l-0MR8NUQgNTyUMzfgwOJqmZgzVhUCvhIQD1vdxWD3aWlCsbuW6CAMb5zPLga8A6zK2HnKI9vRyOYRAO_3qOlnCjtE6DzOua7yQRu4T0yJ9KYuzK8dd5Qp_zGmHxetMKQtQSjB1iLTZ75saB510rfqiqQ",
          'x-amzn-accept-type': 'com.amazon.dash.replenishment.DrsSlotStatusResult@1.0',
          'x-amzn-type-version': 'com.amazon.dash.replenishment.DrsSlotStatusInput@1.0',
          'Content-Type': 'application/json',
          'Content-Length': Buffer.byteLength(data)
  }
};

var req = https.request(options, function(res) {
      res.setEncoding('utf8');
      res.on('data', function (chunk) {
          console.log('\n');
          console.log(today);
        console.log(data);
        console.log('\n');
          console.log('statusCode:', res.statusCode);
          console.log("body: " + chunk);
            console.log("sucessfully called slot status");


      });
  });

  req.write(data);
  req.end();

}

exports.Slot_Status_function = Slot_Status_function;
