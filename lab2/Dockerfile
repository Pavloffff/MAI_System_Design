FROM ghcr.io/userver-framework/ubuntu-22.04-userver-pg-dev:latest AS builder

WORKDIR /app
COPY . .

RUN rm -rf build* \
    && make build-release

RUN useradd -m appuser
WORKDIR /app

EXPOSE 8080
USER appuser

CMD ["make", "start-release"]