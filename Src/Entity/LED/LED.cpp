#include "LED.hpp"

void LED_off(enum LED_COLOR color)
{
    if (color == LED_RED)
    {
        HAL_GPIO_WritePin(LED_PORT, LED_RED_PIN, LED_STATE_OFF);
    }
    else if (color == LED_GREEN)
    {
        HAL_GPIO_WritePin(LED_PORT, LED_GREEN_PIN, LED_STATE_OFF);
    }
    else if (color == LED_BLUE)
    {
        HAL_GPIO_WritePin(LED_PORT, LED_BLUE_PIN, LED_STATE_OFF);
    }
}

void LED_on(enum LED_COLOR color)
{
    if (color == LED_RED)
    {
        HAL_GPIO_WritePin(LED_PORT, LED_RED_PIN, LED_STATE_ON);
    }
    else if (color == LED_GREEN)
    {
        HAL_GPIO_WritePin(LED_PORT, LED_GREEN_PIN, LED_STATE_ON);
    }
    else if (color == LED_BLUE)
    {
        HAL_GPIO_WritePin(LED_PORT, LED_BLUE_PIN, LED_STATE_ON);
    }
}

void LED_init()
{
    HAL_GPIO_WritePin(LED_PORT, LED_RED_PIN, LED_STATE_ON);
    HAL_GPIO_WritePin(LED_PORT, LED_GREEN_PIN, LED_STATE_ON);
    HAL_GPIO_WritePin(LED_PORT, LED_BLUE_PIN, LED_STATE_ON);
}

void LED_toggle(enum LED_COLOR color)
{
    if (color == LED_RED)
    {
        HAL_GPIO_TogglePin(LED_PORT, LED_RED_PIN);
    }
    else if (color == LED_GREEN)
    {
        HAL_GPIO_TogglePin(LED_PORT, LED_GREEN_PIN);
    }
    else if (color == LED_BLUE)
    {
        HAL_GPIO_TogglePin(LED_PORT, LED_BLUE_PIN);
    }
}

void LED_ALL_OFF(void)
{
    HAL_GPIO_WritePin(LED_PORT, LED_RED_PIN, LED_STATE_OFF);
    HAL_GPIO_WritePin(LED_PORT, LED_GREEN_PIN, LED_STATE_OFF);
    HAL_GPIO_WritePin(LED_PORT, LED_BLUE_PIN, LED_STATE_OFF);
}

void LED_ALL_ON(void)
{
    HAL_GPIO_WritePin(LED_PORT, LED_RED_PIN, LED_STATE_ON);
    HAL_GPIO_WritePin(LED_PORT, LED_GREEN_PIN, LED_STATE_ON);
    HAL_GPIO_WritePin(LED_PORT, LED_BLUE_PIN, LED_STATE_ON);
}

void LED_blink(enum LED_COLOR color, uint32_t fre)
{
}
