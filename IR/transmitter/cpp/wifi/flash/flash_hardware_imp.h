#ifdef __cplusplus
extern "C" {
#endif
const uint8_t* read_flash_data();
int write_flash_data(const uint8_t* data);
#ifdef __cplusplus
}
#endif