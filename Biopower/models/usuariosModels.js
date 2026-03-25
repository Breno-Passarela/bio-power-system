const Database = require("../utils/database");
const banco = new Database();

class UsuariosModels {
  #usuId;
  #usuNome;
  #usuEmail;
  #usuSenha;
  #usuCpfCnpj;
  #usuTypeId;
  #usuAtivo;

  constructor(usuNome, usuEmail, usuSenha, usuCpfCnpj, usuTypeId, usuAtivo = 1, usuId = null) {
    this.#usuId = usuId;
    this.#usuNome = usuNome;
    this.#usuEmail = usuEmail;
    this.#usuSenha = usuSenha;
    this.#usuCpfCnpj = usuCpfCnpj;
    this.#usuTypeId = usuTypeId;
    this.#usuAtivo = usuAtivo;
  }

  get usuId() {
    return this.#usuId;
  }

  set usuId(usuId) {
    this.#usuId = usuId;
  }

  get usuNome() {
    return this.#usuNome;
  }

  set usuNome(usuNome) {
    this.#usuNome = usuNome;
  }

  get usuEmail() {
    return this.#usuEmail;
  }

  set usuEmail(usuEmail) {
    this.#usuEmail = usuEmail;
  }

  get usuSenha() {
    return this.#usuSenha;
  }

  set usuSenha(usuSenha) {
    this.#usuSenha = usuSenha;
  }

  get usuCpfCnpj() {
    return this.#usuCpfCnpj;
  }

  set usuCpfCnpj(usuCpfCnpj) {
    this.#usuCpfCnpj = usuCpfCnpj;
  }

  get usuTypeId() {
    return this.#usuTypeId;
  }

  set usuTypeId(usuTypeId) {
    this.#usuTypeId = usuTypeId;
  }

  get usuAtivo() {
    return this.#usuAtivo;
  }

  set usuAtivo(usuAtivo) {
    this.#usuAtivo = usuAtivo;
  }

  async listar(){
    const sql  = "select * from tb_Usuarios";
    const rows = await banco.ExecutaComando(sql);
    const lista = [];
    for (let i = 0; i < rows.length; i++) {
      const usuarios = new UsuariosModels(
        rows[i]["usu_nome"],
        rows[i]["usu_email"],
        rows[i]["usu_senha"],
        rows[i]["usu_cpf_cnpj"],
        rows[i]["usu_typ_id"],
        rows[i]["usu_ativo"],
        rows[i]["usu_id"]
      );
      lista.push(usuarios);
    }
    return lista;
  }

  async login(){
    const sql  = "select * from tb_Usuarios where usu_email = ? and usu_senha = ? and usu_ativo = 1";
    const rows = await banco.ExecutaComando(sql, [this.#usuEmail, this.#usuSenha]);
    if (rows.length > 0) {
      const usuario = new UsuariosModels(
        rows[0]["usu_nome"],
        rows[0]["usu_email"],
        rows[0]["usu_senha"],
        rows[0]["usu_cpf_cnpj"],
        rows[0]["usu_typ_id"],
        rows[0]["usu_ativo"],
        rows[0]["usu_id"]
      );
      return usuario;
    } else {
      return null;
    }
  }

}

module.exports = UsuariosModels;
