class registerController {
    register(req, res) {
        res.render("register", { layout: false });
    }

    /* registerUser(req, res){
        const { nome, email, senha, cep, estado, cidade, bairro, rua, numero } = req.body;
        
    } */
}

module.exports = registerController;