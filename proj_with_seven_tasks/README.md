# task-09

1. Объединить любые 7 заданий (например, с 02 по 08) в общую структуру каталогов.
Название проекта и компонент произвольные. Новый проект должен удовлетворять следующим условиям.
- Каждое задание должно стать компонентой нового проекта.
- Все задания должны собираться единой структурой файлов
**meson.build**,связанных друг с другом.
- Модульные тесты должны быть в отдельной директории
**test**.
- Заголовочные файлы должны включаться с использованием полного пути,
начинающегося с директории myproject(имя нового проекта).
---
2. Напишите документацию к одной из функций или классу из нового проекта,
используя **Doxygen**. Автоматизируйте сборку документации с помощью **Meson
build**, создав отдельный **run_target** для нее.
