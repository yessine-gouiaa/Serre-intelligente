//fct temperature
setInterval(function ()
{
    var xhttp = new XMLHttpRequest();

    xhttp.onreadystatechange = function()
    {
        if(this.readyState == 4 && this.status == 200)
        {
            document.getElementById("temperature").innerHTML = this.responseText;
        }
    };

    xhttp.open("GET", "/lireTemperature", true);
    xhttp.send();
}, 2000);


//fct temperature de seuil
function tempup() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "seuilup", true);
    xhttp.send();
}

function tempdown() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "seuildown", true);
    xhttp.send();
}

setInterval(function ()
{
    var xhttp = new XMLHttpRequest();

    xhttp.onreadystatechange = function()
    {
        if(this.readyState == 4 && this.status == 200)
        {
            document.getElementById("temp de seuil").innerHTML = this.responseText;
        }
    };

    xhttp.open("GET", "/seuil", true);
    xhttp.send();
}, 2000);


//fct capteur incendie
setInterval(function ()
{
    var xhttp = new XMLHttpRequest();

    xhttp.onreadystatechange = function()
    {
        if(this.readyState == 4 && this.status == 200)
        {
            document.getElementById("statefire").innerHTML = this.responseText;
        }
    };

    xhttp.open("GET", "/incendie", true);
    xhttp.send();
}, 2000);


// fct capteur moisture
setInterval(function ()
{
    var xhttp = new XMLHttpRequest();

    xhttp.onreadystatechange = function()
    {
        if(this.readyState == 4 && this.status == 200)
        {
            document.getElementById("moisturestate").innerHTML = this.responseText;
        }
    };

    xhttp.open("GET", "/moisture", true);
    xhttp.send();
}, 2000);



//fct capteur niv eau
setInterval(function ()
{
    var xhttp = new XMLHttpRequest();

    xhttp.onreadystatechange = function()
    {
        if(this.readyState == 4 && this.status == 200)
        {
            document.getElementById("waterstate").innerHTML = this.responseText;
        }
    };

    xhttp.open("GET", "/wls", true);
    xhttp.send();
}, 2000);

//fct pompe
setInterval(function ()
{
    var xhttp = new XMLHttpRequest();

    xhttp.onreadystatechange = function()
    {
        if(this.readyState == 4 && this.status == 200)
        {
            document.getElementById("pompestate").innerHTML = this.responseText;
        }
    };

    xhttp.open("GET", "/pompe", true);
    xhttp.send();
}, 2000);

setInterval(function ()
{
    var xhttp = new XMLHttpRequest();

    xhttp.onreadystatechange = function()
    {
        if(this.readyState == 4 && this.status == 200)
        {
            document.getElementById("pompe2state").innerHTML = this.responseText;
        }
    };

    xhttp.open("GET", "/pompe2", true);
    xhttp.send();
}, 2000);
setInterval(function ()
{
    var xhttp = new XMLHttpRequest();

    xhttp.onreadystatechange = function()
    {
        if(this.readyState == 4 && this.status == 200)
        {
            document.getElementById("ventstate").innerHTML = this.responseText;
        }
    };

    xhttp.open("GET", "/ventilateur", true);
    xhttp.send();
}, 2000);

//fct led eli mch y5admha cap luminosité
setInterval(function ()
{
    var xhttp = new XMLHttpRequest();

    xhttp.onreadystatechange = function()
    {
        if(this.readyState == 4 && this.status == 200)
        {
            document.getElementById("ledstate").innerHTML = this.responseText;
        }
    };

    xhttp.open("GET", "/luminosite", true);
    xhttp.send();
}, 500);


//fct luminosité de seuil
setInterval(function ()
{
    var xhttp = new XMLHttpRequest();

    xhttp.onreadystatechange = function()
    {
        if(this.readyState == 4 && this.status == 200)
        {
            document.getElementById("luminosite de seuil").innerHTML = this.responseText;
        }
    };

    xhttp.open("GET", "/lumseuil", true);
    xhttp.send();
}, 2000);

function lumup() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "lumseuilup", true);
    xhttp.send();
}

function lumdown() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "lumseuildown", true);
    xhttp.send();
}


setInterval(function ()
{
    var xhttp = new XMLHttpRequest();

    xhttp.onreadystatechange = function()
    {
        if(this.readyState == 4 && this.status == 200)
        {
            document.getElementById("humidite de seuil").innerHTML = this.responseText;
        }
    };

    xhttp.open("GET", "/humidite", true);
    xhttp.send();
}, 2000);

function humup() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "humup", true);
    xhttp.send();
}

function humdown() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "humdown", true);
    xhttp.send();
}