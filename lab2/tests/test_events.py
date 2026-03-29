import pytest
import uuid
from datetime import datetime, timedelta

@pytest.fixture
async def auth_headers(service_client):
    unique_email = f"eventuser_{uuid.uuid4().hex[:8]}@example.com"
    user_data = {
        "email": unique_email,
        "name": "John",
        "surname": "Doe",
        "phone": "+79999999999",
        "password": "strongpassword",
    }

    create_resp = await service_client.post("/users", json=user_data)
    assert create_resp.status == 200

    login_resp = await service_client.post(
        "/users/login",
        json={"email": user_data["email"], "password": user_data["password"]},
    )
    assert login_resp.status == 200
    token = login_resp.json()["token"]
    return {"Authorization": f"Bearer {token}"}


def make_event():
    now = datetime.utcnow()
    return {
        "title": "HighLoad++",
        "description": "Backend conference",
        "event_type": "public",
        "place": "Moscow",
        "start_time": (now - timedelta(days=1)).isoformat() + "Z",
        "end_time": (now + timedelta(days=1)).isoformat() + "Z",
        "user_id": 1,
    }


def make_talk(event_id=0):
    now = datetime.utcnow()
    return {
        "title": "Async C++",
        "description": "Deep dive into userver",
        "start_time": now.isoformat() + "Z",
        "end_time": (now + timedelta(hours=1)).isoformat() + "Z",
        "user_id": 1,
        "event_id": event_id,
    }


@pytest.mark.asyncio
async def test_create_event(service_client, auth_headers):
    response = await service_client.post("/events", json=make_event(), headers=auth_headers)
    assert response.status == 200


@pytest.mark.asyncio
async def test_get_event_talks(service_client, auth_headers):
    event_resp = await service_client.post("/events", json=make_event(), headers=auth_headers)
    event_id = event_resp.json()["id"]

    response = await service_client.get(f"/events/{event_id}/talks", headers=auth_headers)
    assert response.status == 200

@pytest.mark.asyncio
async def test_add_talk_to_event(service_client, auth_headers):
    event_resp = await service_client.post("/events", json=make_event(), headers=auth_headers)
    event_id = event_resp.json()["id"]

    talk_resp = await service_client.post("/talks", json=make_talk(event_id=-1), headers=auth_headers)
    talk_id = talk_resp.json()["id"]

    response = await service_client.put(f"/events/{event_id}/talks/{talk_id}", headers=auth_headers)
    assert response.status == 200