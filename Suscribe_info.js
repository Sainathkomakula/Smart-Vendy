

//sucessfull

var request = require('request');
var access_token_DRS;

var Subscr_function = function Sub_function(access_token_DRS ) {
//sucessfull
var options = { method: 'GET',
  url: 'https://dash-replenishment-service-na.amazon.com/subscriptionInfo',
  headers:
   { 'postman-token': '3c220f05-a5cb-b50f-0750-058578f4055f',
     'cache-control': 'no-cache',
     'x-amzn-type-version': 'com.amazon.dash.replenishment.DrsSubscriptionInfoInput@1.0',
     'x-amzn-accept-type': 'com.amazon.dash.replenishment.DrsSubscriptionInfoResult@1.0',
     'Authorization': 'Bearer ' + access_token_DRS // Atza|IwEBIAj-O7u9wQKy91U2VaA7aFrrp5SzTAfY6J_kuyEVw0ZwUbJU6qNEG-NtK_nnmPeMCNkz7P9qgzu56LIKoZ0j4wqV3borMm5PnvgfltOo3KQGxFWCfbCeaQf5zRPH6c56UxRrcsD9WC4Xt_v2Ldk4yzUsE9mECjgoz-qVcleZQJI_xjyDKoj1vlIhDBgKKVmDkgfU_QtCE4Evb0383a22XCVja1j-rrBjOnv3-OyVnpSuDcMYkDxXNlh8zOea5L90BTKDDvwQYxL2uOpltHyKBjWqDtoW8KAATtgrmbMggHY_8bsJgG2txcNPtNqtvqDT95_1prT_I2LtAHVPCr71vGgGVzetF5WVXT6LqeYD4TYnW510WMVMdQYK3sxbDkzrOv_Xc3O9-Zdl7KZb8uL8V1EcTBaGliVdzBjMQ6UXDs-dJw'
    } };

request(options, function (error, response, body) {
  if (error) throw new Error(error);
  console.log('\n');
  console.log(body);
    console.log('\n');
  console.log("sucessfully called subscriptionInfo")
});

}
exports.Subscr_function = Subscr_function;
