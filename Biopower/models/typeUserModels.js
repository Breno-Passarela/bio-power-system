const Database = require("../utils/database");
const banco = new Database();

class TypeUsuariosModels {
  #typId;
  #typDescricao;

  constructor(typId = null, typDescricao) {
    this.#typId = typId;
    this.#typDescricao = typDescricao;
  }

  get typId() {
    return this.#typId;
  }

  set typId(typId) {
    this.#typId = typId;
  }

  get typDescricao() {
    return this.#typDescricao;
  }

  set typDescricao(typDescricao) {
    this.#typDescricao = typDescricao;
  }

  listarTiposUsuarios() {
    let sql = "  select * from tb_typeUser";
    let rows = banco.ExecutaComando(sql);
    let lista = [];
    for (let i = 0; i < rows.length; i++) {
      let typeUser = new TypeUsuariosModels(rows[i]["typ_id"], rows[i]["typ_descricao"]);
      lista.push(typeUser);
    }
    return lista;
  }
}

module.exports = TypeUsuariosModels;
