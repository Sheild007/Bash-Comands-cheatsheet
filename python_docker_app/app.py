import os
import redis
from http.server import BaseHTTPRequestHandler, HTTPServer

# Connect to Redis using the hostname defined in docker-compose.yml
redis_host = os.getenv("REDIS_HOST", "redis")
cache = redis.Redis(host=redis_host, port=6379)

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # Increment a counter in Redis
        count = cache.incr("hits")
        
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()
        
        response = f"<h1>Hello from Python!</h1><p>This page has been viewed {count} times.</p>"
        self.wfile.write(response.encode('utf-8'))

if __name__ == '__main__':
    server = HTTPServer(('0.0.0.0', 8000), RequestHandler)
    print("Starting server on port 8000...")
    server.serve_forever()
