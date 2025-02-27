#pragma once


/**
 * \brief IDrawable Interface for drawable objects
 */
class IDrawable {

	/**
	 * \brief friend class to write renderer->Draw(object) instead of object.Draw(renderer)
	 */
	friend class Renderer;

protected:
	/**
	 * \brief Draw the object to the renderer
	 * \param deviceContext -> the dx11 deviceContext / renderer->GetDeviceContext()
	 */
	virtual void Draw(class ID3D11DeviceContext* deviceContext) = 0;
};