################################################################################
#                                    BUILD                                     #
################################################################################

FROM alpine:3.22.2 AS builder

RUN apk add --no-cache "openssl=~3.5.4"

RUN openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
    -keyout /etc/ssl/private/nginx-selfsigned.key \
    -out /etc/ssl/certs/nginx-selfsigned.crt \
    -subj "/C=FR/ST=Auvergne-Rhône-Alpes/L=Charbonnières-les-Bains/O=42 Lyon/OU=Students/CN=localhost"

################################################################################
#                                     RUN                                      #
################################################################################

FROM alpine:3.22.2 AS runner

COPY --from=builder /etc/ssl/private/nginx-selfsigned.key \
                    /etc/ssl/private/nginx-selfsigned.key
COPY --from=builder /etc/ssl/certs/nginx-selfsigned.crt \
                    /etc/ssl/certs/nginx-selfsigned.crt
COPY nginx.conf /etc/nginx/nginx.conf

# healthcheck prep.
RUN mkdir -p /var/lib/nginx/html/
RUN echo "nginx is alive" | tee /var/lib/nginx/html/health

RUN apk add --no-cache "nginx=~1.28.0"
RUN apk add --no-cache "curl=8.14.1-r2"

# meta
CMD ["nginx", "-g", "daemon off;"]
HEALTHCHECK --interval=30s --timeout=10s --start-period=40s --retries=3 \
  CMD curl -sS --fail https://localhost:443/health --cacert /etc/ssl/certs/nginx-selfsigned.crt || exit 1

