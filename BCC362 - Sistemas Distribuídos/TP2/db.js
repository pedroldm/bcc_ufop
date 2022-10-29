function consultPostgres(pgClient, debug = false) {
    let query = randomQuery();
    if(debug) console.log(`Query ${query[0]} : ` + query[1]);
    pgClient.query(query[1], (err, res) => {
        if(!err) {
            if(debug) console.log(res.rows);
        } else {
            if(debug) console.log(err.message);
        }
    })
}

function randomQuery() {
    let rand = Math.floor(Math.random() * 10);
    switch(rand) {
        case 0 : 
            return [rand, "Select * from accounts_balance"];
        case 1 :
            return [rand, "Select * from accounts_balance where id = " + Math.floor(Math.random() * (999 - 0 + 1) + 0)];
        case 2 : 
            return [rand, "Select balance from accounts_balance where id = " + Math.floor(Math.random() * (999 - 0 + 1) + 0)];
        case 3 :
            return [rand, "Select name from accounts_balance where balance > " + Math.random() * (100000000 - 0 + 1) + 0];
        case 4 :
            return [rand, "Select last_ip from accounts_balance where id = " + Math.floor(Math.random() * (999 - 0 + 1) + 0)];
        case 5 :
            return [rand, "Select username from accounts_balance where id = " + Math.floor(Math.random() * (999 - 0 + 1) + 0)];
        case 6 :
            return [rand, "Select name, username, balance from accounts_balance where balance < " + Math.random() * (100000000 - 0 + 1) + 0];
        default :
            return [rand, "Select name, username, balance from accounts_balance where id = " + Math.floor(Math.random() * (999 - 0 + 1) + 0)];
    }  
}

module.exports = {
    consultPostgres : consultPostgres
}