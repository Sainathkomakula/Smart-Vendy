var request = require('request');
var access_token_DRS;
var slot_number
var slot_ID;
var slot_number_1="bf3f0b71-7851-4b8c-9c6c-7364118d130f";
var slot_number_2="a30ec848-664b-49b5-88d3-80631fbb34ea";
var slot_number_DRS;


var DRS_call_function = function DRS_function(access_token_DRS, slot_number) {
  if(slot_number==1);
  {
    slot_number_DRS=slot_number_1;
  }
   else {
       slot_number_DRS=slot_number_2;
   }
var headers = {
    'Authorization': 'Bearer ' + access_token_DRS,
    'x-amzn-accept-type': 'com.amazon.dash.replenishment.DrsReplenishResult@1.0',
    'x-amzn-type-version': 'com.amazon.dash.replenishment.DrsReplenishInput@1.0'

}
var options = {

    url: 'https://dash-replenishment-service-na.amazon.com/replenish/'+ slot_number_DRS,
    port: 443,
    method: 'POST',
    headers: headers,
}
/*var options_2 = {

    url: 'https://dash-replenishment-service-na.amazon.com/replenish/a30ec848-664b-49b5-88d3-80631fbb34ea',
    port: 443,
    method: 'POST',
    headers: headers,
}

*/
// Start the request

  request(options, function(error, response, body) {
    console.log('statusCode:', response.statusCode);
    console.log('headers:', response.headers);
    // Print out the response body
  //  console.log("HI");
    console.log(body);
        console.log("sucessfully called ordered KitKat");


    if (error) {
        console.log("error = " + error);
    }
})


/*else if(slot_number==2){
  request(options, function(error, response, body) {
    console.log('statusCode:', response.statusCode);
    console.log('headers:', response.headers);
    // Print out the response body
  //  console.log("HI");
    console.log(body);
        console.log("sucessfully called ordered oreo");


    if (error) {
        console.log("error = " + error);
    }
})
}*/


}
exports.DRS_call_function = DRS_call_function;
