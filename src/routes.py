from fastapi import APIRouter


def get_apps_router() -> APIRouter:
    router = APIRouter()
    return router