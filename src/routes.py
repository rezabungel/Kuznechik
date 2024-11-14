from fastapi import APIRouter

from health.router import health_router


def get_apps_router() -> APIRouter:
    router = APIRouter()

    router.include_router(health_router)

    return router