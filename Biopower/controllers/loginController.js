class loginController {
    login(req, res) {
        res.render("login", { layout: false });
    }
}

module.exports = loginController; 