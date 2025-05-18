# Stage 1: Build final image with frontend (static HTML, CSS, JS and API requests proxied to backend via Nginx)
FROM nginx@sha256:aed99734248e851764f1f2146835ecad42b5f994081fa6631cc5d79240891ec9

LABEL author="Rezabungel"

# Remove default conf.d directory before adding custom configs
RUN rm -rf /etc/nginx/conf.d/

# Copy Nginx configuration files
COPY config/frontend/nginx.conf /etc/nginx/nginx.conf
COPY config/frontend/conf.d/ /etc/nginx/conf.d/

# Copy frontend source files (HTML, CSS, JS, images)
COPY src/frontend/ /usr/share/nginx/html/

# Expose port used by Nginx
EXPOSE 80

# Run the Nginx server in the foreground
CMD ["nginx", "-g", "daemon off;"]