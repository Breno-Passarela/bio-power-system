const UsuariosModels = require("../models/usuariosModels");
const products = require("../data/products");

class UsuariosController {
  async autentificacao(req, res) {
    res.render("autentificacao", { layout: false });
  }

  async login(req, res) {
    res.render("login", { layout: false, error: null, form: { email: "" } });
  }

  async loginPost(req, res) {
    const email = (req.body.email || "").trim().toLowerCase();
    const password = (req.body.password || "").trim();

    try {
      const usuarioModel = new UsuariosModels();
      usuarioModel.usuEmail = email;
      usuarioModel.usuSenha = password;

      const usuario = await usuarioModel.login();

      if (!usuario) {
        return res.render("login", {
          layout: false,
          error: "Credenciais inválidas ou usuário inativo.",
          form: { email },
        });
      }

      // Roles em minúsculo para bater com o middleware ensureAdmin
      let role = "client";
      let roleDisplay = "Cliente";
      if (Number(usuario.usuTypeId) === 1) { role = "admin"; roleDisplay = "Administrador"; }
      else if (Number(usuario.usuTypeId) === 2) { role = "staff"; roleDisplay = "Funcionario"; }

      req.session.user = {
        id: usuario.usuId,
        email: usuario.usuEmail,
        role,
        name: usuario.usuNome,
        typeId: usuario.usuTypeId,
        roleDisplay,
      };

      const redirectTo = (role === "admin" || role === "staff") ? "/dashboard" : "/";
      return res.redirect(redirectTo);
    } catch (err) {
      console.error("Erro no login:", err);
      return res.render("login", {
        layout: false,
        error: "Erro ao autenticar. Tente novamente.",
        form: { email },
      });
    }
  }

  async logout(req, res) {
    req.session.destroy(() => {
      res.redirect("/auth");
    });
  }

  async register(req, res) {
    res.render("register", { layout: false });
  }

  async listarUsuarios(req, res) {
      let usuarios = new UsuariosModels();
      let listaUsuarios = await usuarios.listar();
      res.render("dashboard/dashboard", { layout: false, listaUsuarios, products: [], user: req.session.user, flash: null });
  }
}


module.exports = UsuariosController;