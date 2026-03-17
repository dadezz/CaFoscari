FROM python:3.9-slim

WORKDIR /app

COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

COPY src/ .

RUN useradd -m ctf
USER ctf

CMD ["gunicorn", "-w", "4", "-b", "0.0.0.0:1337", "app:app"]