FROM nginx
WORKDIR /var/www
COPY mini_server.c .
COPY ./nginx/nginx.conf /etc/nginx/nginx.conf
RUN apt-get update \
&& apt install -y build-essential \
&& apt install -y libfcgi-dev \
&& apt install -y spawn-fcgi \
&& gcc mini_server.c -o ms.out -lfcgi \
&& rm -rf /var/lib/apt/lists \
&& chown -R nginx:nginx /etc/nginx/nginx.conf \
&& chown -R nginx:nginx /var/cache/nginx \
&& chown -R nginx:nginx /home \
&& touch /var/run/nginx.pid \
&& chown -R nginx:nginx /var/run/nginx.pid
CMD bash -c "spawn-fcgi -p 8080 ./ms.out && nginx -g 'daemon off;'"
USER nginx
HEALTHCHECK --interval=5m --timeout=3s CMD curl -f http://localhost/ || exit 1