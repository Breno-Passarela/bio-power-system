const express = require("express");
const expressEjsLayout = require("express-ejs-layouts");
const session = require("express-session");

/* Paginas */
const homeRoutes = require("./routes/HomeRoutes");
const storeRoutes = require("./routes/StoreRoutes");
const aboutUsRoutes = require("./routes/AboutUsRoutes");
const autentificacaoRoutes = require("./routes/AutentificacaoRoutes");

const adminRoutes = require("./routes/AdminRoutes");
const server = express();
const PORT = 5000;
server.set("view engine", "ejs");
server.set("layout", "./layout.ejs");
server.use(express.static("public"));

server.use(expressEjsLayout);
server.use(express.urlencoded({ extended: true }));
server.use(
  session({
    secret: process.env.SESSION_SECRET ?? "bio_power_secret",
    resave: false,
    saveUninitialized: false,
    cookie: { maxAge: 1000 * 60 * 60 }
  })
);

server.use((req, res, next) => {
  res.locals.sessionUser = req.session.user;
  next();
});

server.use("/", homeRoutes);
server.use("/", autentificacaoRoutes);
server.use("/admin", adminRoutes);
server.use("/store", storeRoutes);
server.use("/about-us", aboutUsRoutes);

server.listen(PORT, () => {
  console.log(`Servidor rodando na porta http://localhost:${PORT}`);
});
