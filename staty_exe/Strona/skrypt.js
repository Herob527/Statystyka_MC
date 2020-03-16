const sciezka = "../wyniki.json";
const tabela = $("#wyniki");
$.getJSON(sciezka, (dane) => {
    let doStrony = "";
    $.each(dane, (key, val) => {
        doStrony += `<tr> <th colspan='2'> &nbsp; </th>  </tr>`;
        doStrony += `<tr> <th colspan='2'> ${key} </th>  </tr>`;
        doStrony += `<tr> <th colspan='2'> &nbsp; </th>  </tr>`;
        $.each(val, (key, val1) => {
            let pomocnicza = val1;
            if (typeof val1 == "object") {
                pomocnicza = val1.toString();
            }
            doStrony += `<tr> <td> ${key}</td> <td> ${pomocnicza} </td> </tr>`;
        })
        tabela.html(doStrony);
    })
})
