################################################################################
#                                    BUILD                                     #
################################################################################

FROM alpine:3.23.0 AS builder

RUN mkdir -p /var/www/html/wordpress

# RUN echo "@testing http://dl-cdn.alpinelinux.org/alpine/testing/testing" >> /etc/apk/repositories
RUN apk add --no-cache \
    "curl=~8" \
    "php85-fpm=~8.5.0" "php85=~8.5.0" "php85-phar=~8.5.0" \
    "php85-openssl=~8.5.0" "php85-mysqli=~8.5.0"

# RUN ln -s /usr/bin/php85 /usr/bin/php

RUN curl -L https://github.com/wp-cli/wp-cli/releases/download/v2.12.0/wp-cli-2.12.0.phar \
    -o /tmp/wp-cli.phar
RUN [ "$(sha256sum /tmp/wp-cli.phar | awk '{print $1}')" = "ce34ddd838f7351d6759068d09793f26755463b4a4610a5a5c0a97b68220d85c" ] || (echo "Checksum mismatch" && exit 1)

RUN php85 -d memory_limit=256M /tmp/wp-cli.phar core download --path=/var/www/html/wordpress

################################################################################
#                                     RUN                                      #
################################################################################

FROM alpine:3.23.0 AS runner

ARG MYSQL_USER=wpuser
ARG MYSQL_DATABASE=wp
ARG INCEPTION_HOST_DB=ft_mariadb 
ARG WP_ADMIN_USER=admin
ARG WP_ADMIN_EMAIL=admin@admin.com
ARG WP_SITE_NAME="Inception's Wordpress"
ARG SITE_NAME=elagouch.42.fr
ENV MYSQL_USER=$MYSQL_USER
ENV MYSQL_DATABASE=$MYSQL_DATABASE
ENV INCEPTION_HOST_DB=$INCEPTION_HOST_DB
ENV WP_ADMIN_USER=$WP_ADMIN_USER
ENV WP_ADMIN_EMAIL=$WP_ADMIN_EMAIL
ENV WP_SITE_NAME=$WP_SITE_NAME
ENV SITE_NAME=$SITE_NAME

RUN mkdir -p /app /var/cache/lighttpd/uploads
WORKDIR /app 

COPY --from=builder /tmp/wp-cli.phar /app/wp-cli
COPY --from=builder /var/www/html/wordpress /var/www/html/wordpress
COPY entrypoint.sh /app/entrypoint.sh
COPY lighttpd.conf /app/lighttpd.conf

# RUN echo "@testing http://dl-cdn.alpinelinux.org/alpine/testing/testing" >> /etc/apk/repositories
RUN apk add --no-cache \
    "php85-fpm=~8.5.0" "php85=~8.5.0" "php85-phar=~8.5.0" \
    "php85-openssl=~8.5.0" "php85-mysqli=~8.5.0" "php85-cgi=~8.5.0" \
    "php85-iconv=~8.5.0" \
    "lighttpd=~1.4.82"

CMD ["sh", "/app/entrypoint.sh"]

