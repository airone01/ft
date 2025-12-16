#!/bin/sh

set -euo pipefail

WP_PATH="/var/www/html/wordpress"
WP_CONFIG="$WP_PATH/wp-config.php"

if [ ! -f "$WP_CONFIG" ]; then
  echo "wp-config.php not found, creating config..."

  export MYSQL_PASSWORD="$(cat /run/secrets/mysql_password)"
  export WP_ADMIN_PASSWORD="$(cat /run/secrets/wordpress_admin_password)"

  php84 /app/wp-cli config create --dbhost=$INCEPTION_HOST_DB --dbname=$MYSQL_DATABASE --dbuser=$MYSQL_USER --dbpass=$MYSQL_PASSWORD --path="$WP_PATH"

  php84 /app/wp-cli core install \
    --url="https://$SITE_NAME" \
    --title="$WP_SITE_NAME" \
    --admin_user="$WP_ADMIN_USER" \
    --admin_password="$WP_ADMIN_PASSWORD" \
    --admin_email="$WP_ADMIN_EMAIL" \
    --path="$WP_PATH"
else
  echo "wp-config.php already exists, skipping config creation."
fi

exec /usr/sbin/php-fpm84 -F

