################################################################################
#                                     RUN                                      #
################################################################################

FROM alpine:3.23.0 AS runner

ARG MYSQL_USER=wpuser
ARG MYSQL_DATABASE=wp
ARG MARIADB_SOCKET=/tmp/mariadbd.sock
ENV MYSQL_USER=$MYSQL_USER
ENV MYSQL_DATABASE=$MYSQL_DATABASE
ENV MARIADB_SOCKET=$MARIADB_SOCKET

RUN apk add --no-cache "mariadb=~11" "mariadb-client=~11"
# opted out mariadb-client

RUN mkdir -p /app /data
COPY entrypoint.sh /app/entrypoint.sh

# configure default tables
RUN mariadb-install-db --datadir='/data'
RUN mkdir -p /etc/my.cnf.d/
COPY mariadbd-server.cnf /etc/my.cnf.d/mariadbd-server.cnf

# metadata
WORKDIR /data
CMD ["sh", "/app/entrypoint.sh"]

HEALTHCHECK --interval=30s --timeout=10s --start-period=30s --retries=3 \
  CMD /usr/bin/mariadb-admin ping -h localhost \
      --socket=$MARIADB_SOCKET || exit 1

