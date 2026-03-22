## Сборка из vscode в devcontainer

1. Скачать репозиторий и открыть его в vscode из директории lab2:
```
git clone https://github.com/Pavloffff/MAI_System_Design.git
cd lab2
code .
```
2. Скачать расширение ms-vscode-remote.remote-containers
3. Открыть проект в vscode и нажать 'Reopen in container'
4. Открыть терминал от пользователя user (можно в vscode Terminal -> New Terminal либо через docker exec и sudo su user)
5. Собрать проект с помощью:
```sh
make build-debug
```
6. Прописать симлинку, чтобы в vscode не было ошибок
```sh
ln -sf build-debug/compile_commands.json .
```