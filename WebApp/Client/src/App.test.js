import { render, screen } from "@testing-library/react";
import App from "./App";

import { MemoryRouter } from "react-router-dom";
import { mount } from "enzyme";
import Home from "./Pages/Home/Home";

describe("Routing Tests", () => {
  test("Main Path Should Load Home Component", () => {
    const wrapper = mount(
      <MemoryRouter initialEntries={["/"]}>
        <App />
      </MemoryRouter>
    );
    expect(wrapper.find(Home)).toHaveLength(1);
  });

  test("Random Path Should Load Home Component", () => {
    const wrapper = mount(
      <MemoryRouter initialEntries={["/random"]}>
        <App />
      </MemoryRouter>
    );
    expect(wrapper.find(Home)).toHaveLength(1);
  });
});
