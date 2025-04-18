FROM ubuntu:20.04

WORKDIR /app

RUN apt-get update && apt-get install -y \
    libicu66 \
    libssl1.1 \
    && rm -rf /var/lib/apt/lists/*

COPY . .

RUN chmod +x /app/lib/AriannaSrv/AriannaSrv

EXPOSE 8080

WORKDIR /app/lib/AriannaSrv
CMD ["./AriannaSrv", "TcpIp"]
