import pytest
import uuid
from datetime import datetime, timedelta

@pytest.fixture
async def auth_headers(service_client):
    unique_email = f"talkuser_{uuid.uuid4().hex[:8]}@example.com"
    user_data = {
        "email": unique_email,
        "name": "John",
        "surname": "Doe",
        "phone": "+79999999999",
        "password": "strongpassword",
    }

    await service_client.post("/users", json=user_data)
    login_resp = await service_client.post(
        "/users/login",
        json={"email": user_data["email"], "password": user_data["password"]},
    )
    token = login_resp.json()["token"]
    return {"Authorization": f"Bearer {token}"}


def make_talk(event_id=1):
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
async def test_create_talk(service_client, auth_headers):
    response = await service_client.post("/talks", json=make_talk(), headers=auth_headers)
    assert response.status == 200


@pytest.mark.asyncio
async def test_get_all_talks(service_client, auth_headers):
    response = await service_client.get("/talks", headers=auth_headers)
    assert response.status == 200