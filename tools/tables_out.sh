#!/bin/bash

# Проверка наличия аргумента с директорией
if [ $# -ne 1 ]; then
    echo "Использование: $0 <выходная_директория>"
    exit 1
fi

OUT_DIR="$1"

# Создаём директорию, если её нет
mkdir -p "$OUT_DIR" || { echo "Ошибка: не удалось создать директорию $OUT_DIR"; exit 1; }

# Awk-обработчик потока
awk -v outdir="$OUT_DIR" '
    BEGIN {
        count = 0                # счётчик таблиц
        state = "HEADER"          # ожидаем заголовок (название таблицы)
        current_file = ""         # текущий выходной файл
    }

    # Пустая строка (или строка только из пробелов) – разделитель таблиц
    /^[[:space:]]*$/ {
        if (state == "DATA") {
            # Закрываем текущий файл, если он был открыт
            if (current_file != "") {
                close(current_file)
                current_file = ""
            }
        }
        state = "HEADER"           # следующая непустая строка будет названием таблицы
        next
    }

    # Состояние HEADER: встретили название таблицы – пропускаем и открываем новый файл
    state == "HEADER" {
        count++
        current_file = outdir "/table" count ".csv"
        state = "DATA"             # теперь пишем данные
        next
    }

    # Состояние DATA: записываем строку в текущий файл
    state == "DATA" {
        if (current_file != "") {
            print > current_file
        }
    }

    END {
        # Если после последней таблицы не было пустой строки – закрываем файл
        if (state == "DATA" && current_file != "") {
            close(current_file)
        }
    }
'
