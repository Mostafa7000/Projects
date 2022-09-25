// Setup empty JS object to act as endpoint for all routes
// Express to run server and routes
let projectData= {};
const express= require('express');

// Start up an instance of app
const app= express();

/* Dependencies */
/* Middleware*/
const bodyParser= require('body-parser');
const cors= require('cors');

//Here we are configuring express to use body-parser as middle-ware.
// Cors for cross origin allowance
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());
app.use(cors());

// Initialize the main project folder
app.use(express.static('website'));

// Spin up the server
// Callback to debug
let port=7000;
const server= app.listen(port,()=>console.log('Server Is Listening'));

// Initialize all route with a callback function
// Callback function to complete GET '/all'
app.get('/all',(req,res)=>{
    res.send(projectData);
});

// Post Route
app.post('/saveData',(req,res)=>{
    let weather= req.body;

    projectData.temp=weather.temp;
    projectData.feel=weather.feel;
    projectData.date=weather.date;

    res.send('Saved successfully');
})