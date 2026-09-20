# ==========================================
# STAGE 1: Build Environment
# ==========================================
FROM node:18-alpine AS builder

# Set the working directory
WORKDIR /app

# COPY package.json and package-lock.json FIRST!
# This takes advantage of Docker's layer caching.
# If dependencies haven't changed, Docker uses the cached layer.
COPY package*.json ./

# Install all dependencies (including devDependencies needed for building)
RUN npm ci

# Now copy the rest of the application code
COPY . .

# Build the application (e.g., compile TypeScript to JavaScript)
RUN npm run build

# ==========================================
# STAGE 2: Production Environment
# ==========================================
# We start fresh from a new, tiny alpine image
FROM node:18-alpine AS production

# Set environment to production (optimizes Node.js performance)
ENV NODE_ENV=production

WORKDIR /app

# Only copy package files again
COPY package*.json ./

# Install ONLY production dependencies (skipping dev tools, saving space)
RUN npm ci --only=production && npm cache clean --force

# Copy ONLY the compiled output from the builder stage
COPY --from=builder /app/dist ./dist

# SECURITY: Change ownership of the app directory to the unprivileged 'node' user
RUN chown -R node:node /app

# SECURITY: Switch from 'root' to 'node' user
USER node

# Expose the port
EXPOSE 3000

# Define the command to run the app
CMD ["node", "dist/index.js"]
