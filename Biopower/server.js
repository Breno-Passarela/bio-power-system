const express = require('express');
const homeRoutes = require('./routes/homeRoutes');
const loginRoutes = require('./routes/LoginRoutes');
const registerRoutes = require('./routes/RegisterRoutes');
const expressEjsLayout = require("express-ejs-layouts");

const server = express();
const PORT = 5000;
server.set('view engine', 'ejs');
server.set("layout", "./layout.ejs")
server.use(express.static('public'))

server.use(expressEjsLayout);
server.use(express.urlencoded({ extended: true }));

server.use('/', homeRoutes);
server.use("/login", loginRoutes);
server.use("/register", registerRoutes);



server.listen(PORT, () => {
    console.log(`Servidor rodando na porta http://localhost:${PORT}`);
});