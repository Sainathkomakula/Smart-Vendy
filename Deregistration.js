var request = require("request");

var deregistration_function = function DeReg_function(access_token_DRS) {
    var options = {
        method: 'DELETE',
        url: 'https://dash-replenishment-service-na.amazon.com/registration',
        headers: {
            'Authorization': 'Bearer ' + access_token_DRS,
            'cache-control': 'no-cache',
            'x-amzn-type-version': 'com.amazon.dash.replenishment.DrsDeregisterInput@2.0',
            'x-amzn-accept-type': 'com.amazon.dash.replenishment.DrsDeregisterResult@1.0',
            //authorization: 'Bearer  Atza|IwEBIHcxhtdKjbu2_N5QT9pE1ZS6eQaxkXVXrhOYjavjwEmE8s9TYIbPyVzPu46EvWqHZXNyjZ33T-n2zSkmoTV26nnpyB8CexOV2axaA-fBJlO59M6Z9QCdY5jwTSbgvU3XnwjgL-atojqmmGz4JjY-0nWZ_erNeZLMbqsYtz-VRqr7pLOXoXfNvkvJZ890ZtOZ7Pqe316UQix9R2LGAOMrNX03B_Mcap9e3M8dJisEUo6mhqdPNVV2t_OEvqtCK_Ld3Q08CsoAueKR52tEs7btosHXt-9uH3kKesCWt8-U9rrPV2x4XfDGjTpKfQMIGjB6JjmFMj9vD2q4moAJ4QceTrPE6qHQy68E5SSks6VcikpzePuqqvEERbL8479paLHP5AGP_Z4RSWAyHlgu8HNFemnQC_Q2V5GKbUQ-gYFhLAI7aA'
        }
    };

    request(options, function(error, response, body) {
        if (error) throw new Error(error);
    console.log('\n');
        console.log(body);
            console.log('\n');
            console.log("Device registration done successfully");
    });
}

exports.deregistration_function = deregistration_function;
