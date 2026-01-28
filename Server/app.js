/**
 * Main Express Application Configuration
 * This file sets up the core Express server with middleware, routes, and deployment settings
 */

const express = require('express');
const cors = require('cors');
const path = require('path');
const cookieParser = require('cookie-parser');

// Initialize Express application
const app = express();

// Enable CORS
app.use(cors({
    origin: "http://localhost:3000", // your frontend URL
    credentials: true,               // allow cookies to be sent
}));

// Environment Configuration
// Load environment variables from config file in development mode
if (process.env.NODE_ENV !== 'production') {
    require('dotenv').config({ path: path.resolve(__dirname, './config/config.env') });
}

// Middleware Configuration
app.use(express.json()); // Parse JSON request bodies
app.use(cookieParser()); // Parse cookies from requests

// Import API Routes
const user = require('./routes/userRoute');
const commentRoutes = require("./routes/commentRoute");
// Mount API Routes with /api/v1 prefix
app.use('/api/v1', user);
app.use("/api/v1", commentRoutes);

// Production vs Development Environment Setup
if (process.env.NODE_ENV === 'production') {
    // Serve static files from React build folder in production
    app.use(express.static(path.join(__dirname, '../client/build')));

    app.get('*', (req, res) => {
        res.sendFile(path.resolve(__dirname, '../client', 'build', 'index.html'));
    });
} else {
    app.get('/', (req, res) => {
        res.send('Server is Running! 🚀');
    });
}

// Export the configured Express application
module.exports = app;