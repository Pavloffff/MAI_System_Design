import pytest
import uuid

@pytest.fixture
async def auth_headers(service_client):
    unique_email = f"testuser_{uuid.uuid4().hex[:8]}@example.com"
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


def make_user_payload():
    unique_email = f"user_{uuid.uuid4().hex[:8]}@example.com"
    return {
        "email": unique_email,
        "name": "John",
        "surname": "Doe",
        "phone": "+79999999999",
        "password": "strongpassword",
    }


@pytest.mark.asyncio
async def test_user_create(service_client):
    response = await service_client.post("/users", json=make_user_payload())
    assert response.status == 200


@pytest.mark.asyncio
async def test_user_login(service_client):
    user_data = make_user_payload()
    await service_client.post("/users", json=user_data)

    response = await service_client.post(
        "/users/login",
        json={"email": user_data["email"], "password": user_data["password"]},
    )
    assert response.status == 200
    assert "token" in response.json()


@pytest.mark.asyncio
async def test_user_get_by_email(service_client, auth_headers):
    user_resp = await service_client.post("/users", json=make_user_payload())
    email = user_resp.json()["email"]

    response = await service_client.get("/users", params={"email": email}, headers=auth_headers)
    assert response.status == 200

@pytest.mark.asyncio
async def test_user_get_by_name(service_client, auth_headers):
    response = await service_client.get(
        "/users/John_Doe",
        headers=auth_headers,
    )
    assert response.status == 200