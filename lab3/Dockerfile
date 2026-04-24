FROM ghcr.io/userver-framework/ubuntu-22.04-userver-pg-dev:latest

ENV CCACHE_DIR=/home/user/lab3/.ccache \
  CORES_DIR=/cores \
  PREFIX=~/.local \
  SHELL=/bin/bash

USER user

WORKDIR /home/user/lab3

COPY . .

RUN make build-release

EXPOSE 8080

CMD ["./build-release/lab3", "--config", "configs/static_config.yaml", "--config_vars", "configs/config_vars.yaml"]