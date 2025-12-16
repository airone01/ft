#!/usr/bin/env sh

/usr/bin/mariadbd --datadir=/data --user=root --socket=$MARIADB_SOCKET & PID=$!
# we don't start with `mariadbd-safe`, as it's just a wrapper around `mariadb`
# which will exit w/ 0 when `mariadbd` is launched.
# see: https://mariadb.com/docs/server/security/securing-mariadb/running-mariadbd-as-root
# see: https://github.com/mariadb-corporation/mariadb-docs/blob/main/server/server-management/starting-and-stopping-mariadb/mariadbd-options.md#--user
# see: https://github.com/mariadb-corporation/mariadb-docs/blob/main/server/ha-and-performance/optimization-and-tuning/system-variables/server-system-variables.md#socket

until /usr/bin/mariadb-admin ping --silent --socket=$MARIADB_SOCKET; do
  echo "Waiting for database to be ready..."
  sleep 2
done

echo "Running DB setup SQL commands..."

if [ ! -f /run/secrets/mysql_password ]; then
  echo "INCEPTION: MYSQL PASSWORD FILE NOT FOUND!"
  exit 1
fi

export MYSQL_PASSWORD=$(cat /run/secrets/mysql_password);

/usr/bin/mariadb -uroot --socket=$MARIADB_SOCKET -e "
CREATE DATABASE IF NOT EXISTS $MYSQL_DATABASE;
CREATE USER IF NOT EXISTS '$MYSQL_USER'@'%' IDENTIFIED BY '$MYSQL_PASSWORD';
CREATE USER IF NOT EXISTS '$MYSQL_USER'@'localhost' IDENTIFIED BY '$MYSQL_PASSWORD';
GRANT ALL PRIVILEGES ON $MYSQL_DATABASE.* TO '$MYSQL_USER'@'%';
GRANT ALL PRIVILEGES ON $MYSQL_DATABASE.* TO '$MYSQL_USER'@'localhost';
FLUSH PRIVILEGES;" 2>&1 | tee /dev/stderr

echo "DB setup complete. Shutting down temp instance..."
/usr/bin/mariadb-admin --socket=$MARIADB_SOCKET -u root shutdown
wait $PID

echo "Starting MariaDB as PID 1..."
# replace the current shell process with mariadb
# mariadb becomes PID 1 and receives signals from Docker
exec /usr/bin/mariadbd --datadir=/data --user=root --socket=$MARIADB_SOCKET

