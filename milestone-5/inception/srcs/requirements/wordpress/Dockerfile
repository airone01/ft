################################################################################
#                                    BUILD                                     #
################################################################################

FROM alpine:3.22.2 AS builder

RUN mkdir -p /var/www/html/wordpress

# RUN echo "@testing http://dl-cdn.alpinelinux.org/alpine/testing/testing" >> /etc/apk/repositories
RUN apk add --no-cache \
    "curl=~8" \
    "php84-fpm=~8.4" "php84=~8.4" "php84-phar=~8.4" \
    "php84-openssl=~8.4" "php84-mysqli=~8.4"

# RUN ln -s /usr/bin/php84 /usr/bin/php

RUN curl -L https://github.com/wp-cli/wp-cli/releases/download/v2.12.0/wp-cli-2.12.0.phar \
    -o /tmp/wp-cli.phar
RUN [ "$(sha256sum /tmp/wp-cli.phar | awk '{print $1}')" = "ce34ddd838f7351d6759068d09793f26755463b4a4610a5a5c0a97b68220d85c" ] || (echo "Checksum mismatch" && exit 1)

RUN php84 -d memory_limit=256M /tmp/wp-cli.phar core download --path=/var/www/html/wordpress

################################################################################
#                                     RUN                                      #
################################################################################

FROM alpine:3.22.2 AS runner

ARG MYSQL_USER=wpuser
ARG MYSQL_DATABASE=wp
ARG INCEPTION_HOST_DB=mariadb 
ARG WP_ADMIN_USER=supervisor
ARG WP_ADMIN_EMAIL=supervisor@supervisor.com
ARG WP_SITE_NAME="Inception's Wordpress"
ARG SITE_NAME=elagouch.42.fr
ENV MYSQL_USER=$MYSQL_USER
ENV MYSQL_DATABASE=$MYSQL_DATABASE
ENV INCEPTION_HOST_DB=$INCEPTION_HOST_DB
ENV WP_ADMIN_USER=$WP_ADMIN_USER
ENV WP_ADMIN_EMAIL=$WP_ADMIN_EMAIL
ENV WP_SITE_NAME=$WP_SITE_NAME
ENV SITE_NAME=$SITE_NAME

RUN mkdir -p /app
WORKDIR /app 

COPY --from=builder /tmp/wp-cli.phar /app/wp-cli
COPY --from=builder /var/www/html/wordpress /var/www/html/wordpress
COPY entrypoint.sh /app/entrypoint.sh

# RUN echo "@testing http://dl-cdn.alpinelinux.org/alpine/testing/testing" >> /etc/apk/repositories
RUN apk add --no-cache \
    "php84-fpm=~8.4" "php84=~8.4" "php84-phar=~8.4" \
    "php84-openssl=~8.4" "php84-mysqli=~8.4" "php84-cgi=~8.4" \
    "php84-iconv=~8.4"

# 2. Configure PHP-FPM to listen on port 9000
RUN sed -i 's/listen = 127.0.0.1:9000/listen = 9000/g' /etc/php84/php-fpm.d/www.conf

# 3. FIX: Ensure listen.allowed_clients is commented out!
# If it is uncommented, it restricts access to localhost, causing the 502 error.
# This command ensures the line starts with a semicolon (;).
RUN sed -i 's/^listen.allowed_clients/;listen.allowed_clients/g' /etc/php84/php-fpm.d/www.conf

# # listen on all interfaces
# RUN sed -i 's/listen = 127.0.0.1:9000/listen = 9000/g' /etc/php84/php-fpm.d/www.conf
# # ensure we allow all clients
# RUN sed -i 's/;listen.allowed_clients/listen.allowed_clients/g' /etc/php84/php-fpm.d/www.conf

CMD ["sh", "/app/entrypoint.sh"]

