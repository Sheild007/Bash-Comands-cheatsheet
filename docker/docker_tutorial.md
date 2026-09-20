# Docker and Docker Compose Best Practices

Writing a *good* Dockerfile is the difference between a secure, 50MB image that builds in seconds, and an insecure, 2GB image that takes 10 minutes to build.

## 1. The Anatomy of a Perfect Dockerfile

Here are the golden rules for writing production-ready Dockerfiles:

### Rule 1: Use Small, Specific Base Images
Instead of `FROM ubuntu` or `FROM node:18`, use `FROM node:18-alpine` or `FROM python:3.10-slim`. This drastically reduces the attack surface and download times.

### Rule 2: Optimize Layer Caching
Docker builds layers sequentially and caches them. If a layer changes, all subsequent layers are rebuilt.
**Bad:** Copying everything, then installing dependencies.
**Good:** Copying *only* `package.json` (or `requirements.txt`), installing dependencies, and *then* copying the rest of your code. This means changing your source code won't force Docker to reinstall all your libraries!

### Rule 3: Use Multi-Stage Builds
Compiling code often requires heavy tools (like `gcc` or Go). You don't need these in production!
Multi-stage builds allow you to use a heavy image to build the app, and then copy *only the compiled binary* into a tiny, fresh production image.

### Rule 4: Never Run as Root
By default, Docker containers run as root. If a hacker escapes the container, they have root access to the host machine. Always create a dedicated user and switch to it using the `USER` directive.

### Rule 5: Use a `.dockerignore` File
Just like `.gitignore`, this prevents you from copying your local `.git` folder, `node_modules`, or secret `.env` files into the Docker image.

---

## 2. A "Good" Dockerfile Example

*(We have created a sample `Dockerfile` in this directory demonstrating these practices for a Node.js app).*

Notice in our sample:
1. It uses `node:18-alpine` (Small base).
2. It sets `NODE_ENV=production`.
3. It copies `package.json` *before* the source code (Caching).
4. It switches to the built-in `node` user instead of root (Security).

---

## 3. The Anatomy of a Perfect `docker-compose.yml`

Docker Compose is used to define and run multi-container applications (e.g., your App + a Database + a Redis cache).

### Rule 1: Use Named Volumes for Persistent Data
If you spin down a database container, all data is lost. Always map database data directories to a Docker **Named Volume** so it persists across restarts.

### Rule 2: Use Environment Variables securely
Never hardcode passwords in the compose file. Use `${DB_PASSWORD}` and put the actual password in a `.env` file that is ignored by Git.

### Rule 3: Use `depends_on` and `healthcheck`
If your App needs the Database to be ready before it starts, just saying `depends_on: db` isn't enough (it only waits for the container to start, not for PostgreSQL to actually be ready to accept connections). You must define a `healthcheck` on the DB, and tell the App to wait for it to be `healthy`.

### Rule 4: Set Restart Policies
Use `restart: unless-stopped` so your containers automatically boot back up if they crash or if the host server reboots.

---

## 4. A "Good" Docker Compose Example

*(We have created a sample `docker-compose.yml` in this directory demonstrating a secure App + PostgreSQL setup).*

Notice in our sample:
1. It uses `.env` variables.
2. It has a `healthcheck` on the database.
3. The web app waits for the database to be `condition: service_healthy`.
4. It uses a named volume `pgdata` to save database state.

---

## Exercises
1. Look at the `Dockerfile` in this folder. Try to identify which lines are responsible for layer caching.
2. Look at the `docker-compose.yml`. What command does it run to check if the database is actually ready?
3. Run `docker-compose config` in this folder. It validates the YAML and prints the final configuration it will use. (Note: You may see warnings about missing `.env` variables).
