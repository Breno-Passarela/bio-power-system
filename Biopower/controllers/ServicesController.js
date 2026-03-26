const ServicosModels = require("../models/servicosModels");
const ServicosContratadosModels = require("../models/servicosContratadosModels");

class ServicesController {
  constructor() {
    this.servicosModel = new ServicosModels();
    this.contratosModel = new ServicosContratadosModels();
  }

  async page(req, res) {
    let services = [];
    let meusServicos = [];
    const user = req.session.user;

    try {
      services = await this.servicosModel.listar();
    } catch (err) {
      console.error("Erro ao listar serviços:", err);
      services = [];
    }

    if (user) {
      try {
        meusServicos = await this.contratosModel.listarPorCliente(user.id);
      } catch (err) {
        console.error("Erro ao listar serviços contratados:", err);
        meusServicos = [];
      }
    }

    res.render("services", { layout: true, services, meusServicos });
  }

  async contratar(req, res) {
    const user = req.session.user;
    if (!user) return res.status(401).json({ ok: false, msg: "Faça login para contratar um serviço." });

    const { servicoId, observacoes } = req.body;
    const id = parseInt(servicoId, 10);
    if (Number.isNaN(id)) return res.status(400).json({ ok: false, msg: "Serviço inválido." });

    try {
      await this.contratosModel.criar({
        clienteId: user.id,
        servicoId: id,
        status: "pendente",
        observacoes: observacoes || null,
      });
      return res.json({ ok: true, msg: "Solicitação registrada." });
    } catch (err) {
      console.error("Erro ao contratar serviço:", err);
      return res.status(500).json({ ok: false, msg: "Erro ao registrar solicitação." });
    }
  }
}

module.exports = ServicesController;
