FROM python:3.11-slim

WORKDIR /app

# Install redis dependency
RUN pip install redis

COPY app.py .

EXPOSE 8000

CMD ["python", "app.py"]
