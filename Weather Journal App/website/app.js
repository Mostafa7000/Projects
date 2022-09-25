/* Global Variables */

// Create a new date instance dynamically with JS
let d = new Date();
let newDate = d.getDate()+'/'+ (d.getMonth()+1) +'/'+ d.getFullYear();

// Personal API Key for OpenWeatherMap API
const APIKey = '8cd630ddde6add9bb07dbc95c103f07f';

// Event listener to add function to existing HTML DOM element
document.getElementById('generate').addEventListener('click',getWeather);

/* Function called by event listener */
function getWeather(event){
    let zip=document.getElementById('zip').value;
    if(zip.length==0)
    {
        alert('Please enter zip code number');
        return;
    }
    let feeling= document.getElementById('feelings').value;

    const APIURL= `https://api.openweathermap.org/data/2.5/weather?zip=${zip},${'us'}&appid=${APIKey}&units=${'metric'}`;

    getAPIData(APIURL)
    .then((data)=>{
        postEndpointData('/saveData',{temp: data.main.temp, date: newDate, feel: feeling});
    })
    .then(()=>{
        retrieveData();
    })
    .catch((error)=>{
        console.log('An error happened ', error);
    });
}
/* Function to GET Web API Data*/
async function getAPIData(url){
    const response= await fetch(url);
    try{
        if(!response.ok)
        {
            let err= Error('Status not 200');
            err.response=response;
            throw err;
        }
        console.log('try');
        weatherData= await response.json();
        console.log(weatherData);
        return weatherData;
    }
    catch(error){
        alert('Can\'t fetch data');
        throw error;
    }
}

/* Function to POST data */
async function postEndpointData(url,data){
    const response= await fetch(url,{
        method: 'POST',
        credentials: 'same-origin',
        headers:{
            'Content-Type': 'application/json'
        },
        body: JSON.stringify(data)
    })
    try{
        res= await response.text();
        console.log(res); //'Saved successfully'
        return res;
    }
    catch(error){
        console.log('error',error);
    }
}

/* Function to GET Project Data */
async function retrieveData(){
    response= await fetch('/all');
    try{
        const myData= await response.json();
        console.log(myData);

        document.getElementById('temp').innerHTML = Math.round(myData.temp)+ ' degrees';
        document.getElementById('content').innerHTML = myData.feel;
        document.getElementById('date').innerHTML = myData.date;
    }
    catch(error){
        console.log('An error happened',error);
    }
}