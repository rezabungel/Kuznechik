from contextlib import nullcontext as does_not_raise

import pytest

from encryption.kuznechik import Kuznechik
from config.utils import get_lib_path


class TestKuznechik:

    @pytest.fixture(scope='class')
    def kuznechik(self):
        return Kuznechik(get_lib_path('kuznechik.so'))

    @pytest.mark.parametrize(
        'blk, key, expected_result, expectation',
        [
            (bytes.fromhex('48656c6c6f'), bytes.fromhex('576f726c64'), bytes.fromhex('8479704f8d801853d314e7e060f67a80'), does_not_raise()),
        ]
    )
    def test_encrypt(self, kuznechik, blk, key, expected_result, expectation):
        with expectation:
            assert kuznechik.encrypt(blk, key) == expected_result

    @pytest.mark.parametrize(
        'blk, key, expected_result, expectation',
        [
            (bytes.fromhex('8479704f8d801853d314e7e060f67a80'), bytes.fromhex('576f726c64'), bytes.fromhex('48656c6c6f'), does_not_raise()),
        ]
    )
    def test_decrypt(self, kuznechik, blk, key, expected_result, expectation):
        with expectation:
            assert kuznechik.decrypt(blk, key) == expected_result

    @pytest.mark.parametrize(
        'input_bytes, target_size, expected_result, expectation',
        [
            (bytes.fromhex('48656c6c6f'), 16, bytes.fromhex('000000000000000000000048656c6c6f'), does_not_raise()),
            (bytes.fromhex('576f726c64'), 32, bytes.fromhex('000000000000000000000000000000000000000000000000000000576f726c64'), does_not_raise()),
            (bytes.fromhex('54657374'), 4, bytes.fromhex('54657374'), does_not_raise()),
            (bytes.fromhex('546865204269672054657374'), 1, bytes.fromhex('546865204269672054657374'), does_not_raise()),
        ]
    )
    def test_zero_padding(self, kuznechik, input_bytes, target_size, expected_result, expectation):
        with expectation:
            assert kuznechik.zero_padding(input_bytes, target_size) == expected_result

    @pytest.mark.parametrize(
        'padded_bytes, expected_result, expectation',
        [
            (bytes.fromhex('000000000000000000000048656c6c6f'), bytes.fromhex('48656c6c6f'), does_not_raise()),
            (bytes.fromhex('000000000000000000000000000000000000000000000000000000576f726c64'), bytes.fromhex('576f726c64'), does_not_raise()),
            (bytes.fromhex('54657374'), bytes.fromhex('54657374'), does_not_raise()),
            (bytes.fromhex('54657374000000'), bytes.fromhex('54657374000000'), does_not_raise()),
        ]
    )
    def test_remove_zero_padding(self, kuznechik, padded_bytes, expected_result, expectation):
        with expectation:
            assert kuznechik.remove_zero_padding(padded_bytes) == expected_result
