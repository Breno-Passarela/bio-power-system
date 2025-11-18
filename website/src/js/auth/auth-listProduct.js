var dados = [
  {
    id: 1,
    name: "Creatina",
    descricao: "descricao muito massa sobre a Creatina",
    price: 10.0,
    quantidade: 2,
  },
  {
    id: 2,
    name: "Whey de Chocolate",
    descricao: "descricao muito massa sobre o whey",
    price: 15.5,
    quantidade: 5,
  },
  {
    id: 3,
    name: "Cafeina",
    descricao: "Descrição muito massa sobre a cafeina",
    price: 7.25,
    quantidade: 10,
  },
];

function montarTabela() {
  let tbody = document.querySelector("#grid tbody");
  let html = "";

  for (let item of dados) {
    html += `
      <tr>
        <td class="text-center">
          <input type="checkbox" class="check-row" data-id="${item.id}">
        </td>
        <td class ="coluna">${item.id}</td>
        <td class="coluna">${item.name}</td>
        <td class="coluna">${item.descricao}</td>
        <td class="coluna">R$ ${item.price.toFixed(2)}</td>
        <td class="coluna">${item.quantidade}</td>

        <td class="text-center">
          <button class="btn btn-sm btn-danger" onclick="removerProduto(${
            item.id
          })">
            <i class="fa fa-trash"></i>
          </button>
        </td>
      </tr>
    `;
  }

  tbody.innerHTML = html;
}

function adicionarProduto() {
  let vId = document.querySelector("#id-produto").value;
  let vnome = document.querySelector("#nome-produto").value;
  let vdescricao = document.querySelector("#descricao-produto").value;
  let vprice = parseFloat(document.querySelector("#price-produto").value);
  let vquantidade = parseInt(
    document.querySelector("#quantidade-produto").value
  );

  if (
    vnome === "" ||
    vdescricao === "" ||
    isNaN(vprice) ||
    isNaN(vquantidade)
  ) {
    alert("Por favor, preencha todos os campos corretamente.");
    vId.focus();
  } else {
    let novoItem = {
      id: new Date().getTime(),
      name: vnome.value,
      descricao: vdescricao.value,
      price: vprice.value,
      quantidade: vquantidade.value,
    };
    dados.push(novoItem);
    montarTabela();
    vId.value = "";
    vnome.value = "";
    vdescricao.value = "";
    vprice.value = "";
    vquantidade.value = "";
    vId.focus();
    alert("Produto adicionado com sucesso!");
  }
}

function RemoverProduto(idDelete) {
  let listaAux = [];
  if (((let = 0), i < dados.length, i++)) {
    if (dados[i].quantidade != 0) listaAux.push(dados[i]);
  }
  dados = listaAux;
  montarTabela();
}

function removerSelecionados() {
  let listaSelec = document.querySelectorAll(".check-row:checked");
  if (listaSelec.length > 0) {
    for (let ck of listaSelec) {
      if (ck.checked) {
        RemoverProduto(ck.dataset.id);
      }
    }
  }else{
    alert("Nenhum produto selecionado para remoção.");
  }
}

function selecionaTodos(){
    let listaCK = document.querySelectorAll(".check-row");
    let ckTodos = document.querySelector("#ck-todos");
    for(let ck of listaCK){
        ck.checked = ckTodos.checked;
    } 
}

document.addEventListener("DOMContentLoaded", function () {
    montarTabela();

    var btnAdd = document.querySelector("#btn-add-produto");
    btnAdd.addEventListener("click", adicionarProduto, false);
    
    var btnRemover = document.querySelector("#btn-remover-selecionados");
    btnRemover.addEventListener("click", removerSelecionados, false);

    var ckTodos = document.querySelector("#ck-todos");
    ckTodos.addEventListener("change", selecionaTodos, false);
}, false);

