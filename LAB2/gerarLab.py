from pathlib import Path
import re
import sys
import zipfile


# Nome do arquivo ZIP definido manualmente.
# Ele não precisa ser igual ao nome da pasta atual,
# mas deve seguir o formato nome_completo_em_minusculo_RA.zip.
NOME_ZIP = "davi_honorio_de_brito_pontes_9389.zip"


ARQUIVOS_OBRIGATORIOS = {
    "main.c",
    "ces11_pqueue.c",
    "ces11_pqueue.h",
    "ces11_vector.c",
    "ces11_vector.h",
}


def nome_base_valido(nome):
    """
    Verifica nomes no formato:

        douglas_adams_4242
        joao_da_silva_123456
    """

    padrao = r"^[a-z]+(?:_[a-z]+)*_[0-9]+$"
    return re.fullmatch(padrao, nome) is not None


def nome_zip_valido(nome_zip):
    """
    Verifica se o nome do ZIP está no formato:

        nome_completo_em_minusculo_RA.zip
    """

    if not nome_zip.lower().endswith(".zip"):
        return False

    nome_sem_extensao = Path(nome_zip).stem

    return nome_base_valido(nome_sem_extensao)


def encontrar_arquivos_codigo(pasta):
    """
    Procura arquivos .c e .h dentro da pasta atual
    e também dentro de suas subpastas.
    """

    return [
        arquivo
        for arquivo in pasta.rglob("*")
        if (
            arquivo.is_file()
            and arquivo.suffix.lower() in {".c", ".h"}
        )
    ]


def validar_projeto(pasta, arquivos_codigo):
    erros = []

    # Valida o nome da pasta atual
    # if not nome_base_valido(pasta.name):
    #     erros.append(
    #         f"O nome da pasta '{pasta.name}' não está no formato "
    #         "nome_completo_em_minusculo_RA."
    #     )

    # Valida o nome do ZIP definido no código
    #if not nome_zip_valido(NOME_ZIP):
    #    erros.append(
    #        f"O nome do ZIP '{NOME_ZIP}' não está no formato "
    #        "nome_completo_em_minusculo_RA.zip."
    #    )

    if not arquivos_codigo:
        erros.append("Nenhum arquivo .c ou .h foi encontrado.")

    nomes_encontrados = {
        arquivo.name
        for arquivo in arquivos_codigo
    }

    # Verifica os arquivos obrigatórios
    for arquivo_obrigatorio in sorted(ARQUIVOS_OBRIGATORIOS):
        if arquivo_obrigatorio not in nomes_encontrados:
            erros.append(
                f"Arquivo obrigatório não encontrado: "
                f"{arquivo_obrigatorio}"
            )

    # Verifica se existe exatamente um arquivo chamado main.c
    arquivos_main = [
        arquivo
        for arquivo in arquivos_codigo
        if arquivo.name == "main.c"
    ]

    if len(arquivos_main) == 0:
        erros.append(
            "O arquivo que contém a função main deve se chamar main.c."
        )
    elif len(arquivos_main) > 1:
        erros.append(
            "Foi encontrado mais de um arquivo chamado main.c."
        )

    return erros


def criar_zip(pasta, arquivos_codigo):
    """
    Cria o ZIP na pasta acima da pasta atual.

    Exemplo:

        douglas_adams_4242/
        └── arquivos do código

        douglas_adams_4242.zip
    """

    caminho_zip = pasta.parent / NOME_ZIP

    with zipfile.ZipFile(
        caminho_zip,
        mode="w",
        compression=zipfile.ZIP_DEFLATED
    ) as arquivo_zip:

        for arquivo in arquivos_codigo:
            caminho_relativo = arquivo.relative_to(pasta)

            # Mantém a pasta do projeto dentro do arquivo ZIP
            caminho_no_zip = Path(pasta.name) / caminho_relativo

            arquivo_zip.write(
                arquivo,
                arcname=str(caminho_no_zip)
            )

    return caminho_zip


def main():
    # Usa a pasta em que o comando foi executado
    pasta = Path.cwd()

    print(f"Procurando arquivos em: {pasta}")
    print(f"Nome do ZIP definido: {NOME_ZIP}")

    arquivos_codigo = encontrar_arquivos_codigo(pasta)

    erros = validar_projeto(
        pasta,
        arquivos_codigo
    )

    if erros:
        print("\nValidação falhou:")

        for erro in erros:
            print(f"- {erro}")

        sys.exit(1)

    caminho_zip = criar_zip(
        pasta,
        arquivos_codigo
    )

    print("\nValidação concluída com sucesso.")
    print(
        f"Arquivos .c e .h encontrados: "
        f"{len(arquivos_codigo)}"
    )
    print(f"Arquivo ZIP criado em: {caminho_zip}")


if __name__ == "__main__":
    main()
